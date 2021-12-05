class C1 {
  public static int var=C2.var+1;
  public static void main(String args[]) {
    System.out.println("C1.var = "+C1.var);
    System.out.println("C2.var = "+C2.var);
  }
}
