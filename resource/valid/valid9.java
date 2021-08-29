// check return

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));
    }
}

class TV {
    public int Start(int num) {
        return num; // OK
        // return true; // not boolean
        // return test; // no test variable
    }
}
