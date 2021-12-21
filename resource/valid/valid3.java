// check "this"

class Factorial {
    public static void main(String[] a) {
        System.out.println(new Fac().ComputeFac(10));
    }
}

class Fac {
    public int ComputeFac(int num) {
        int num_aux;

        num_aux = this.ComputeFac(num - 1);  // OK
        // num_aux = this.Test(num - 1);     // No Test() method

        return num_aux;
    }
}
