
import java.util.HashSet;
import java.util.Iterator;

public class SET<T> implements Iterable<T> {
    private HashSet<T> set;

    public SET() {
        this.set = new HashSet<>();
    }

    public boolean isEmpty() {
        return set.isEmpty();
    }

    public int size() {
        return set.size();
    }

    public boolean contains(T element) {
        return set.contains(element);
    }

    public void add(T element) {
        set.add(element);
    }

    public void addAll(SET<T> other) {
        set.addAll(other.set);
    }

    public void retainAll(SET<T> other) {
        set.retainAll(other.set);
    }

    public void clear() {
        set.clear();
    }

    @Override
    public Iterator<T> iterator() {
        return set.iterator();
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("{");
    
        Iterator<T> it = set.iterator();
        while (it.hasNext()) {
            sb.append(it.next());
            if (it.hasNext()) sb.append(',');   // avoid trailing comma
        }
    
        sb.append('}');
        return sb.toString();
    }
    

} 