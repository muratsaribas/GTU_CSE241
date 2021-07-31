/**
 *
 * @param <E> generic
 */
public class Iterator<E> {
    private E[] iteratorArr;
    private int current = 0;
    private boolean removed = false;

    /**
     *
     * @param arr array
     * @throws Exception ex
     */
    public Iterator(E[] arr) throws Exception{
        if (arr == null) throw new Exception();
        else
            iteratorArr = arr;
    }
    /**
     * @return true if the iteration has more elements.
     *
     */
    boolean hasNext(){
        return current < iteratorArr.length;
    }

    /**
     *
     * @return next element in the iteration and advances the iterator.
     * @throws Exception
     */
    E next() throws Exception{
        if (current >= iteratorArr.length)
            throw new Exception();
        E temp = iteratorArr[current];
        current++;
        removed = false;
        return temp;
    }

    /**
     * Removes from the underlying collection the last element returned
     * by this iterator
     */
    void remove() throws Exception {
        if (current==0 || removed)
            throw new Exception();
        iteratorArr[current-1] = null;
        removed = true;

    }




}
