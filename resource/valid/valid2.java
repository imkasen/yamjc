// check parameters

class TreeVisitor {
    public static void main(String[] a) {
        Tree wood;
        System.out.println(new TV().Start(3, true, wood));     // OK
        // System.out.println(new TV().Start(3, true));        // Parameter numbers are wrong
        // System.out.println(new TV().Start(3, true, test));  // no test variable
    }
}

class TV {
    public int Start(int num1, boolean bln, Tree wood) {
        Tree root;
        boolean ntb;

        root = new Tree();

        ntb = root.Init(1);        // OK
        // ntb = root.Init(root);  // parameter type does not match
        // ntb = root.Init(true);  // parameter type does not match

        return num1;
    }
}

class Tree {
    public boolean Init(int num) {
        return true;
    }
}

