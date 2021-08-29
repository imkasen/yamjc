// check if and while

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3)); // OK
    }
}

class TV {
    public int Start(int num) {
        Tree root;
        boolean ntb;

        root = new Tree();

        // if (true) // OK
        // if (1) // not boolean
        // {}
        // else {}

        // while (true) // OK
        // while (1) // not boolean
        // {}

        return num;
    }
}

class Tree {
    public boolean Init(int num) {
        return true;
    }
}
