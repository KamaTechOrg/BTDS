package com.lmscoder.ds;

import java.util.HashMap;

public class MAP<K, V> {
    private HashMap<K, V> map;

    public MAP() {
        this.map = new HashMap<>();
    }

    public boolean isEmpty() {
        return map.isEmpty();
    }

    public int size() {
        return map.size();
    }

    public boolean containsKey(K key) {
        return map.containsKey(key);
    }

    public V get(K key) {
        return map.get(key);
    }

    public void put(K key, V value) {
        map.put(key, value);
    }

    public void remove(K key) {
        map.remove(key);
    }

    public void clear() {
        map.clear();
    }
    
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("{");
    
        java.util.Iterator<java.util.Map.Entry<K,V>> it = map.entrySet().iterator();
        while (it.hasNext()) {
            java.util.Map.Entry<K,V> e = it.next();
            Object key = e.getKey();
            Object value = e.getValue();
            sb.append(key instanceof String ? "\"" + key + "\"" : key)
              .append(':')
              .append(value instanceof String ? "\"" + value + "\"" : value);
            if (it.hasNext()) sb.append(',');       // no trailing comma
        }
    
        sb.append('}');
        return sb.toString();
    }
    

} 