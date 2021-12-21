// check assignment

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));           // OK
        // System.out.println(new TV().Start(1+2));      // OK
        // System.out.println(new TV().Start(1+false));  // different type
    }
}

class TV {
    public int Start(int num) {
        Tree root;
        boolean ntb;

        root = new Tree();
        ntb = root.Init(1);
        // ntb = root.Init(1+2);     // OK
        // ntb = root.Init(1+true);  // different type
        // ntb = 1;                  // different type
        // root = true;              // different type
        // root = root.Init(1);      // different type

        return num;
    }
}

class Tree {
    public boolean Init(int num) {
        return true;
    }
}
