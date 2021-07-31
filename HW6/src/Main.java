public class Main {

    public static void main(String[] args) throws Exception {

        System.out.println("---Test ArrayList---");

        ArrayList<String> arr1;
        arr1 = new ArrayList<String>();
        ArrayList<String> arr2;
        arr2 = new ArrayList<String>();
        ArrayList<String> arr3;
        arr3 = new ArrayList<String>();
        System.out.println("---Test add()---");
        arr1.add("ABC");
        arr1.add("123");
        arr1.add("ABD");
        arr1.add("cba");
        arr1.add("mrt");
        arr1.print();

        System.out.println("---Test remove()---");
        arr1.remove("ABC");
        arr1.print();


        arr2.add("E1");
        arr2.add("E2");
        arr2.add("E3");
        arr2.add("E4");
        System.out.println("---Test addAll()---");
        arr1.addAll(arr2);
        arr1.print();

        System.out.println("---Test contains()---");
        System.out.println(arr1.contains("E1"));
        System.out.println(arr2.contains("E1"));
        System.out.println(arr1.contains("123"));
        System.out.println(arr2.contains("123"));

        System.out.println("---Test containsAll()---");
        System.out.println(arr1.containsAll(arr2));
        System.out.println(arr2.containsAll(arr1));

        System.out.println("---Test retainAll()---");
        arr1.retainAll(arr2);
        arr1.print();

        System.out.println("---Test clear()---");
        arr1.clear();
        arr1.print();

        System.out.println("---Test isEmpty()---");
        System.out.println(arr1.isEmpty());

        System.out.println("---Test size()---");
        System.out.println(arr1.size());
        System.out.println(arr2.size());

        System.out.println("---Test removeAll()---");
        arr3.add("E2");
        arr3.add("E3");
        arr2.removeAll(arr3);
        arr2.print();


        System.out.println("---Test HashSet---");

        HashSet<String> hash1;
        hash1 = new HashSet<String>();
        HashSet<String> hash2;
        hash2 = new HashSet<String>();
        HashSet<String> hash3;
        hash3 = new HashSet<String>();

        System.out.println("---Test add()---");
        hash1.add("AA");
        hash1.add("BB");
        hash1.add("CC");
        hash1.add("DD");
        hash1.add("FF");
        hash1.print();

        System.out.println("---Test add()---");
        hash2.add("BA");
        hash2.add("CB");
        hash2.add("DC");
        hash2.add("FD");
        hash2.print();

        System.out.println("---Test add()---");
        hash3.add("FD");
        hash3.add("FF");
        hash3.print();

        System.out.println("---Test addAll()---");
        hash1.addAll(hash2);
        hash1.print();
        System.out.println("Size: "+ hash1.size());
        System.out.println("--------");
        hash1.addAll(hash3);
        hash1.print();
        System.out.println("Size: "+hash1.size());

        System.out.println("--------");
        hash2.addAll(arr2);
        hash2.print();

        System.out.println("---Test remove()---");
        hash1.remove("AA");
        hash1.print();

        System.out.println("---Test removeAll()---");
        hash1.removeAll(hash2);
        hash1.print();

        System.out.println("---Test contains()---");
        System.out.println(hash1.contains("BB"));
        System.out.println(hash1.contains("AA"));

        System.out.println("---Test containsAll()---");
        System.out.println(hash1.containsAll(arr1));
        System.out.println(hash1.containsAll(hash1));

        System.out.println("---Test retainAll()---");
        HashSet<String> hash4;
        hash4 = new HashSet<String>();
        hash4.add("BB");
        hash4.add("BA");
        hash1.retainAll(hash4);
        hash1.print();

        System.out.println("---Test clear()---");
        hash4.clear();
        hash4.print();

        System.out.println("---Test isEmpty()---");
        System.out.println(hash4.isEmpty());
        System.out.println(hash1.isEmpty());

    }
}
