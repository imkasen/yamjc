// check System.out.println()

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));  // OK
        // System.out.println(new TV());        // not int
    }
}

class TV {
    public int Start(int num) {
        Tree root;
        boolean ntb;

        // System.out.println(1);     // OK
        // System.out.println(true);  // not int
        // System.out.println(root);  // not int

        return num;
    }
}

class Tree {
    public boolean Init(int num) {
        return true;
    }
}
