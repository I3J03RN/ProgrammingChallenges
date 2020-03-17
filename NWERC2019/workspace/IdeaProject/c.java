import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Scanner;

public class c
{

    static class P {
        int start, end;
        public P(int s, int e) {
            start = s;
            end = e;
        }
    }

    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        int canvases = s.nextInt();
        P[] coords = new P[canvases];
        for (int i = 0; i < canvases; i++) {
            coords[i] = new P(s.nextInt(), s.nextInt());
        }
        int pegAmount = s.nextInt();
        ArrayList<Integer> pegs = new ArrayList<>();
        for (int i = 0; i < pegAmount; i++) {
            pegs.add(s.nextInt());
        }

        int[] needed = new int[canvases];
        for (int i = 0; i < canvases; i++) {
            needed[i] = 2;
            for (int j = 0 ; j < pegs.size(); j++ ) {
                if (pegs.get(j) >= coords[i].start && pegs.get(j) <= coords[i].end)
                    needed[i]--;
            }
        }

        for(int n : needed) {
            if(n < 0) {
                System.out.println("impossible");
                return;
            }
        }

        ArrayList<Integer> res = new ArrayList<>();
        for (int i = 0; i < canvases; i++) {
            if (needed[i] == 0) continue;


            //next adj
            if (i+1 != canvases && needed[i+1] > 0 && coords[i].end == coords[i+1].start && !pegs.contains(coords[i].end)) {
                    needed[i]--;
                    needed[i+1]--;
                    res.add(coords[i].end);
                    pegs.add(coords[i].end);
            }

            //at start
            if (needed[i] > 0 && (i == 0 || coords[i - 1].end != coords[i].start) && !pegs.contains(coords[i].start)) {
                res.add(coords[i].start);
                pegs.add(coords[i].start);
                needed[i]--;
            }
            //between
            int ind = coords[i].start+1;
            while (needed[i] > 0 && ind < coords[i].end) {
                if(!pegs.contains(ind)) {
                    pegs.add(ind);
                    res.add(ind);
                    needed[i]--;
                }
                ind++;
            }
            // at end
            if (needed[i] > 0 &&
                    (i + 1 == canvases || coords[i].end != coords[i + 1].start) &&
                    !pegs.contains(coords[i].end)) {
                res.add(coords[i].start);
                pegs.add(coords[i].start);
                needed[i]--;
            }

            if(needed[i] > 0) {
                System.out.println("impossible");
                return;
            }

        }
        System.out.println(res.size());
        for (int p : res) {
            System.out.print(p + " ");
        }

        s.close();
    }
}
