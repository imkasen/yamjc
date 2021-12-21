// check return

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));
    }
}

class TV {
    public int Start(int num) {
        TV tv;

        return num;      // OK
        // return true;  // not match
        // return test;  // no test variable
        // return tv;    // not match
    }

    public TV test() {
        TV tv;
        tv = new TV();

        return tv;  // OK
    }

    public int[] test2() {
        int[] number;

        return number;  // OK
    }

}
