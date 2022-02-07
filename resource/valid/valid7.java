// check if and while

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));  // OK
    }
}

class TV {
    public int Start(int num) {
        Tree root;
        boolean ntb;
        boolean ntb2;

        root = new Tree();

        if (true)             // OK
        // if (ntb && ntb2)   // OK
        // if (true && 1)     // not boolean
        // if (root.Init(1))  // OK
        // if (1)             // not boolean
        // if (!false)        // OK
        // if (!1)            // not boolean
        // if (!root.Init(1)) // OK
        {}
        else {}

        while (true)             // OK
        // while (root.Init(1))  // OK
        // while (1)             // not boolean
        {}

        return num;
    }
}

class Tree {
    public boolean Init(int num) {
        return true;
    }
}
