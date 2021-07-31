/**
 *
 * @param <E> generic
 */
public class HashSet<E> implements Set<E>{
    private E[] arr;
    private Iterator<E> iter;

    public HashSet(){
        arr = (E[]) new Object[0];
    }

    @Override
    public Iterator<E> iterator() {
        return iter;
    }

    @Override
    public void add(E e) throws Exception {
        if (!contains(e))
        {
            E[] temp = (E[]) new Object[arr.length+1];
            for (int i=0; i< arr.length; i++)
                temp[i] = arr[i];

            temp[arr.length] = e;
            arr = temp;

            iter = new Iterator<E>(arr);
        }
    }

    @Override
    public void addAll(Collection<E> c) throws Exception {
        for (int i=0; i<c.size(); i++)
            add(c.iterator().next());
        iter = new Iterator<E>(arr);
    }

    @Override
    public void clear() {
        arr = (E[]) new Object[0];
    }

    @Override
    public boolean contains(E e) {
        for (E value : arr) {
            if (value == e)
                return true;
        }
        return false;
    }

    @Override
    public boolean containsAll(Collection<E> c) throws Exception {
        iter = new Iterator<E>(arr);
        while (c.iterator().hasNext()) {
            if (!contains(c.iterator().next()))
                return false;
        }
        return true;
    }

    @Override
    public boolean isEmpty() {
        return arr.length == 0;
    }

    @Override
    public void remove(E e) {
        int deleted = 0;
        for (E item : arr)
            if (item == e)
                deleted++;

        E[] temp = (E[]) new Object[arr.length - deleted];

        int idx = 0;
        for (E value : arr)
            if (value != e) {
                temp[idx] = value;
                idx++;
            }


        arr = (E[]) new Object[arr.length - deleted];
        arr = temp;
    }

    @Override
    public void removeAll(Collection<E> c) throws Exception {
        iter = new Iterator<E>(arr);
        while (c.iterator().hasNext()) {
            E tempE = c.iterator().next();
            if (contains(tempE))
                remove(tempE);
        }
    }

    @Override
    public void retainAll(Collection<E> c) throws Exception {
        iter = new Iterator<E>(arr);
        E[] temp = (E[]) new Object[arr.length];
        int idx=0;
        while (c.iterator().hasNext())
        {
            E tempE = c.iterator().next();
            if(contains(tempE))
            {
                temp[idx] = tempE;
                idx++;
            }
        }
        arr = (E[]) new Object[idx];
        for (int i=0;i<idx;i++)
            arr[i] = temp[i];
    }

    @Override
    public int size() {
        return arr.length;
    }

    void print()
    {
        if (arr != null)
            for (E e : arr) System.out.println(e);
    }
}
