CustomData* mData;

void controller_receiver (NiceAgent *agent,
                           guint stream_id,
                           guint component_id,
                           guint len,
                           gchar *buf,
                           gpointer data);
/*
 * 1. Create agent
 * 2. Create stream_id
 * 3. Set receiver
 * 4. Wait until send_audio done
 * 5. Start gathering candidate
 */
void*  controller (CustomData *data)
{
    // Use for later
    mData = data;

    // Create the nice agent
    data->agent = libnice_create_NiceAgent_without_gstreamer(controller_gathering_done,
                                                             data->context);

    // Create a new stream with one component
    data->stream_id = libnice_create_stream_id (data->agent);

    // Set receiver function
    set_receiver (data->agent, data->stream_id, data->context);

    // Wait until send_audio done
    while(*send_audio_gathering_done == FALSE)
        usleep(100);

    // Start gathering candidates
    libnice_start_gather_candidate (data->agent,
                                    data->stream_id,
                                    data->context);
}


void set_receiver ( NiceAgent *agent,
                    guint stream_id,
                    GMainContext *context)
{
    nice_agent_attach_recv( agent,
                            stream_id,
                            1,
                            context,
                            controller_receiver,
                            NULL);
}

void controller_receiver (  NiceAgent *agent,
                            guint stream_id,
                            guint component_id,
                            guint len,
                            gchar *buf,
                            gpointer data)
{
    if (len == 1 && buf[0] == '\0') {
        g_main_loop_quit (mData->main_loop);
    }
}
