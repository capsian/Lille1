class Example1 {

  static Example1    o1=new Example1();
  static Example1bis o2=new Example1bis();

  Example1() {
    System.out.println("hello from Example1()");
  }
  
  public static void main(String args[]) {
    System.out.println("hello from Example1.main()");
  }
}
