#include "libnice_initialize.h"

NiceAgent *libnice_create_NiceAgent_with_gstreamer ( gboolean *signal_type,
                                                     CustomData *data)
{
    NiceAgent *agent;

    // Create the nice agent
    agent = nice_agent_new( g_main_loop_get_context (gloop),
                            NICE_COMPATIBILITY_RFC5245);
    if (agent == NULL) {
        return NULL;
    }

    GST_INFO ("Initializing libnice with gstreamer: %s:%d, mode=%d",
              data->stun_ip_address,
              data->stun_port,
              data->controlling_mode);

    // Set the STUN settings and controlling mode
    g_object_set(G_OBJECT(agent),
                 "stun-server",
                 data->stun_ip_address,
                 NULL);

    g_object_set(G_OBJECT(agent),
                 "stun-server-port",
                 data->stun_port,
                 NULL);

    g_object_set(G_OBJECT(agent),
                 "controlling-mode",
                 data->controlling_mode,
                 NULL);

    // Connect to the signals
    g_signal_connect(G_OBJECT(agent),
                     "candidate-gathering-done",
                     G_CALLBACK(libnice_candidate_gathering_done),
                     signal_type);

    g_signal_connect(G_OBJECT(agent),
                     "component-state-changed",
                     G_CALLBACK(libnice_component_state_changed),
                     NULL);

    data->agent = agent;
    return agent;
}

guint libnice_create_stream_id (NiceAgent *agent, gchar *stream_name)
{
  guint stream_id;

  GST_INFO ("libnice started adding stream");
  stream_id = nice_agent_add_stream(agent, 1);
  GST_INFO ("libnice add stream");

  if (stream_id == 0) {
    GST_ERROR("Failed to add stream");
  }
  nice_agent_set_stream_name (agent, stream_id, stream_name);
  return stream_id;
}

int libnice_start_gather_candidate (NiceAgent *agent, guint stream_id, GMainContext *context)
{
    if (!nice_agent_gather_candidates(agent, stream_id)) {
        return 1;
    }

    return 0;
}

void  libnice_candidate_gathering_done (NiceAgent *agent, guint stream_id, gboolean *signal_type)
{
    GST_INFO ("libnice_candidate_gathering_done");
    gchar *local_info = (gchar*)malloc(181);
    gchar *remote_info = (gchar*)malloc(181);

    memset(local_info, '\0', 181);
    memset(remote_info, '\0', 181);

    GST_INFO ("Before libnice_print_local_data");
    libnice_print_local_data (agent, stream_id, 1, local_info);

    GST_INFO ("Before libnice_parse_remote_data");
    libnice_parse_remote_data (agent,
                               stream_id,
                               1,
                               remote_info);

    GST_INFO ("Completed: libnice_candidate_gathering_done");
    (*signal_type) = TRUE;
}

void libnice_print_local_data (NiceAgent *agent, guint stream_id, guint component_id, gchar* local_info)
{
  gchar *sdp, *sdp64;

  // Candidate gathering is done. Send our local candidates on stdout
  GST_INFO ("Copy this line to remote client:");
  sdp = nice_agent_generate_local_sdp (agent);
  sdp64 = g_base64_encode ((const guchar *)sdp, strlen (sdp));
  GST_INFO ("\n  %s\n", sdp64);
  g_free (sdp);
  g_free (sdp64);
}

void libnice_parse_remote_data (NiceAgent *agent,
                                guint stream_id,
                                guint component_id,
                                gchar* remote_info)
{
  gchar *sdp;
  gchar *line = NULL;

  GIOChannel* io_stdin;

  io_stdin = g_io_channel_unix_new(fileno(stdin));
  g_io_channel_set_flags (io_stdin, G_IO_FLAG_NONBLOCK, NULL);

  // Listen on stdin for the remote candidate list
  printf("Enter remote data (single line, no wrapping):\n");
  printf("> ");
  fflush (stdout);

  while (TRUE) {
    GIOStatus s = g_io_channel_read_line (io_stdin, &line, NULL, NULL, NULL);
    if (s == G_IO_STATUS_NORMAL) {
      gsize sdp_len;

      sdp = (gchar *) g_base64_decode (line, &sdp_len);
      // Parse remote candidate list and set it on the agent
      if (sdp && nice_agent_parse_remote_sdp (agent, sdp) > 0) {
        g_free (sdp);
        g_free (line);
        break;
      } else {
        fprintf(stderr, "ERROR: failed to parse remote data\n");
        printf("Enter remote data (single line, no wrapping):\n");
        printf("> ");
        fflush (stdout);
      }
      g_free (sdp);
      g_free (line);
    } else if (s == G_IO_STATUS_AGAIN) {
      usleep (100000);
    }
  }
}

void libnice_component_state_changed(NiceAgent *agent, guint stream_id,
    guint component_id, guint state, gboolean signal_type)
{
    if (state == NICE_COMPONENT_STATE_READY)
    {
        g_mutex_lock(&negotiate_mutex);
        negotiation_done = TRUE;
        g_cond_signal(&negotiate_cond);
        g_mutex_unlock(&negotiate_mutex);

        NiceCandidate *local, *remote;

        // Get current selected candidate pair and print IP address used
        if (nice_agent_get_selected_pair (  agent,
                                            stream_id,
                                            component_id,
                                            &local, &remote))
        {
            gchar ipaddr[INET6_ADDRSTRLEN];

            nice_address_to_string(&local->addr, ipaddr);
            nice_address_to_string(&remote->addr, ipaddr);
        }
    }
    else if (state == NICE_COMPONENT_STATE_FAILED)
    {
        g_main_loop_quit (gloop);
    }
}

void libnice_new_selected_pair( NiceAgent *agent, guint stream_id,
                                guint component_id,
                                gchar *lfoundation,
                                gchar *rfoundation,
                                gboolean signal_type)
{
    return;
}
