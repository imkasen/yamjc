class RecursiveSum {
    public static void main(String[] a){
        System.out.println(new Test().Sum(10000));
    }
}

class Test {
    public int Sum(int num) {
        int sum;
        if (num < 2)
            sum = 1;
        else
            sum = num + this.Sum(num - 1);
        return sum;
    }
}