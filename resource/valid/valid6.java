// check assignment

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));  // OK
    }
}

class TV {
    public int Start(int num) {
        int[] number;
        int n;

        number = new int[10];       // OK
        // number = new int[true];  // can not be "true"
        // number[0] = 1;           // OK
        // number[0] = true;        // can not be "true"
        // number[0] = test;        // no test variable
        // number[true] = 1;        // can not be "true"
        // n = number.length;       // OK
        // root = number.length;    // different type

        return num;
    }
}

class Tree {
    public boolean Init(int num) {
        return true;
    }
}
