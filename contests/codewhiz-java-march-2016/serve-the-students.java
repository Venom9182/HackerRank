import java.io.*;
import java.util.*;

class Student{
  private int token;
  private String fname;
  private double cgpa;
  public Student(int id, String fname, double cgpa) {
    super();
    this.token = id;
    this.fname = fname;
    this.cgpa = cgpa;
  }
  public int getToken() {
    return token;
  }
  public String getFname() {
    return fname;
  }
  public double getCgpa() {
    return cgpa;
  }
}

class StudentComparator implements Comparator<Student> {
  @Override
  public int compare(Student x, Student y) {
    int r = Double.compare(y.getCgpa(), x.getCgpa());
    if (r != 0) return r;
    r = x.getFname().compareTo(y.getFname());
    if (r != 0) return r;
    return Integer.compare(x.getToken(), y.getToken());
  }
}

public class Solution {

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int m = Integer.parseInt(in.nextLine());
    PriorityQueue<Student> pq = new PriorityQueue<Student>(new StudentComparator());
    while (m-- > 0) {
      String op = in.next();
      if (op.equals("ENTER")) {
        String name = in.next();
        double cgpa = in.nextDouble();
        int token = in.nextInt();
        pq.add(new Student(token, name, cgpa));
      } else
        pq.poll();
    }
    if (pq.isEmpty())
      System.out.println("EMPTY");
    else
      while (! pq.isEmpty())
        System.out.println(pq.poll().getFname());
  }
}
