// check Class.Method() exists or not

class TreeVisitor {
    public static void main(String[] a) {
        System.out.println(new TV().Start(3));       // OK
        // System.out.println(new Test());           // No Test class
        // System.out.println(new TV().Test(3));     // No Test() method.
        // System.out.println(new Test().Start(3));  // No Test class
    }
}

class TV {
    public int Start(int num) {
        Tree root;
        Flower rose;
        boolean ntb;

        root = new Tree();     // OK
        // root = new Test();  // No Test Class

        rose = new Flower();   // OK
        ntb = rose.Hello();    // OK
        // ntb = rose.Test();  // No Test() method

        ntb = root.Init(1);     // OK, if Tree() exists
        // ntb = root.Test(1);  // No Test() method

        return num;
    }
}

class Tree {
    public boolean Init(int num) {
        return true;
    }
}

class Flower {
    public boolean Hello()
    {
        return true;
    }
}