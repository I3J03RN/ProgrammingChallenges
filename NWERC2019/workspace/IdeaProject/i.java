import java.util.Scanner;

public class i {

    public static void main(String[] args) {

        Scanner s = new Scanner(System.in);
        final int count = s.nextInt();
        int inp = 0, last = -1;
        int index = 1;
        int mp = 1;
        int prevmax = -1;

        while ((inp = s.nextInt()) >= last) {
            if (inp > last) {
                mp = index;
                prevmax = last;
            }
            last = inp;
            index++;
            if (!s.hasNext()) {
                System.out.println("1 1");
                return;
            }
        }

        last = inp;

        if (!s.hasNext()) {
            if (mp == 1) {
                System.out.println("1 " + count);
                return;
            }
            else {
                System.out.println("impossible");
                return;
            }
        }

        //end of > chain

        final int start = mp;
        final int max = inp;

        while ((inp = s.nextInt()) <= last) {
            if (inp < prevmax) {
                System.out.println("impossible");
                return;
            }
            last = inp;
            index++;
            if (!s.hasNext()) {
                System.out.println(mp + " " + count);
                return;
            }
        }

        last = inp;

        final int end = index;  //ob1?

        if(!s.hasNext()) {
            System.out.println(start + " " + end);
            return;
        }

        while ((inp = s.nextInt()) >= last) {
            last = inp;
            index++;
            if(!s.hasNext()) {
                System.out.println(start + " " + end);
                return;
            }
        }

        System.out.println("impossible");

        s.close();

    }


}
