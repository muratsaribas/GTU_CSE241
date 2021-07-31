/**
 *
 * @param <E> generic
 */
public interface Queue<E> extends Collection<E> {
    /**
     * Inserts the specified element into this queue
     * @param e e
     */
    void add(E e);

    /**
     *
     * @return Retrieves, but does not remove, the head of this queue.
     */
    E element();

    /**
     * Inserts the specified element into this queue
     * @param e e
     */
    void offer(E e);

    /**
     *
     * @return Retrieves and removes the head of this queue, or throws if this
     * queue is empty.
     */
    E pool();
}
