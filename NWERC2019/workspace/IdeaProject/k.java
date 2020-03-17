import java.util.ArrayList;
import java.util.Scanner;

class Island {
    int le;
    int ri;
    int width;

    Island(int le, int ri) {
        this.le = le;
        this.ri = ri;
        updw();
    }
    void updw() {
        this.width = ri-le;
    }
}

public class k {

    static boolean efficient;

    static int watertime(int dist) {
        if (efficient) {
            return dist;                        //swimm all
        } else {
            if (dist % d < t) return dist / d * t + dist%d; //swimm last step
            else return dist / d * t + t;                   //jump last
        }
    }

    static int racel,d,t;
    static ArrayList<Island> islands;
    static boolean[] land;

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        racel = s.nextInt();
        d = s.nextInt();
        t = s.nextInt();

        int n = s.nextInt();
        efficient =  (double) d / (double) t <= 1;
        if (n == 0) {
            System.out.println(watertime(racel));
            return;
        }

        islands = new ArrayList<>(n);
        land = new boolean[racel+1];



        //scanning
        //first
        int il = s.nextInt();
        int ir = s.nextInt();
        Island last = new Island(il, ir);
        for (int j = il+1; j < ir; j++) {
            land[j] = true;
        }
        islands.add(last);

        for (int i = 1; i < n; i++) {
            il = s.nextInt();
            ir = s.nextInt();

            if (ir - last.le < d) { //connect them
                for (int j = last.ri; j < ir; j++) {
                    land[j] = true;
                }
                last.ri = ir;
                last.updw();
            } else {
                last = new Island(il, ir);
                islands.add(last);
                for (int j = il+1; j < ir; j++) {
                    land[j] = true;
                }
            }
        }

        //search jump path
        int pos = 0;
        int sumtime = 0;
        islandLoop:
        for (Island i : islands) {
            for (int jumpl = d; jumpl >= i.width; jumpl--) {
                for (int start = (pos + jumpl) < i.ri ? i.ri-jumpl : pos; start <= i.le; start++) {
                    if (start+jumpl <= racel && !land[start + jumpl]) {
                        //System.out.println("jump from: " + start + " to " + (start+jumpl));
                        sumtime += watertime(start - pos);
                        sumtime += t;
                        pos = start+jumpl;
                        continue islandLoop;
                    }
                }
            }
        }

        sumtime += watertime(racel - pos);

        System.out.println(sumtime);
    }
}
