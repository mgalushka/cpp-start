public class MainLoader {

  static {
    System.loadLibrary("mainloader");
  }

  private native String get(String key);
  private native void put(String key, String value);

  public static void main(String [] args) {
    System.out.println("Testing JNI");

    new MainLoader().put("key1", "test value 1");
  }
}
