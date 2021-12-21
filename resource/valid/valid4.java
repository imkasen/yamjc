// check declarations

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));
    }
}

class TV {
    Tree ttt;     // OK
    boolean nta;  // OK
    int i;        // OK

    public int Start(int num) {
        Tree root;    // OK
        boolean ntb;  // OK
        int[] j;      // OK

        // Test test1;  // No Test Class

        return num;
    }
}

class Tree {
    int i;

    public boolean Init(int num) {
        return true;
    }
}
