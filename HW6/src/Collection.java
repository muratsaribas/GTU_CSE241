/**
 *
 * @param <E> generic
 */
public interface Collection<E> {
    /**
     *
     * @return iterator
     */
    Iterator<E> iterator();

    /**
     * Ensures that this collection contains the specified element.
     * @param e e
     * @throws Exception ex
     */
    void add(E e) throws Exception;

    /**
     * Adds all of the elements in the specified collection to this collection
     * @param c c
     * @throws Exception ex
     */
    void addAll(Collection<E> c) throws Exception;

    /**
     * Removes all of the elements from this collection
     */
    void clear();

    /**
     *
     * @param e e
     * @return true if this collection contains the specified element.
     */
    boolean contains(E e);

    /**
     *
     * @param c c
     * @return Returns true if this collection contains all of the elements in the
     * specified collection
     * @throws Exception ex
     */
    boolean containsAll(Collection<E> c) throws Exception;

    /**
     *
     * @return true if this collection contains no elements
     */
    boolean isEmpty();

    /**
     * Removes a single instance of the specified element from this
     * collection, if it is present
     * @param e e
     * @throws Exception ex
     */
    void remove(E e) throws Exception;

    /**
     * Removes all of this collection's elements that are also contained
     * in the specified collection
     * @param c c
     * @throws Exception ex
     */
    void removeAll(Collection<E> c) throws Exception;

    /**
     * Retains only the elements in this collection that are contained in
     * the specified collection
     * @param c c
     * @throws Exception ex
     */
    void retainAll(Collection<E> c) throws Exception;

    /**
     *
     * @return the number of elements in this collection.
     */
    int size();
}
