class SumWhileAnd {
    public static void main(String[] a){
        System.out.println(new Test().Sum(100));
    }
}

class Test {
    public int Sum(int num) {
        int sum;
        sum = 0;
        while (0 < num && sum < 1000) {
            System.out.println(sum);
            sum = sum + num;
            num = num - 1;
        }
        return sum;
    }
}

/*
 * result:
 * 0
 * 100
 * 199
 * 297
 * 394
 * 490
 * 585
 * 679
 * 772
 * 864
 * 955
 * 1045
 */
