package com.lmscoder.ds;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

public class BT<T> {
    public static class Node<T> {
        T data;
        Node<T> left;
        Node<T> right;

        Node(T data) {
            this.data = data;
            this.left = null;
            this.right = null;
        }
    }

    private Node<T> root;

    public BT() {
        this.root = null;
    }

    public void setRoot(Node<T> root) {
        this.root = root;
    }

    public Node<T> getRoot() {
        return root;
    }

    private void printNode(Node<T> node, StringBuilder sb, String prefix, String childrenPrefix) {
        if (node == null) {
            return;
        }

        sb.append(prefix);
        sb.append(node.data);
        sb.append('\n');

        if (node.left != null || node.right != null) {
            if (node.right != null) {
                printNode(node.right, sb, childrenPrefix + "├── ", childrenPrefix + "│   ");
            }
            if (node.left != null) {
                printNode(node.left, sb, childrenPrefix + "└── ", childrenPrefix + "    ");
            }
        }
    }

    @Override
    public String toString() {
        if (root == null) return "BT()";

        //— 1. collect nodes level-order —//
        List<Object> level = new ArrayList<>();
        Queue<Node<T>> q = new LinkedList<>();
        q.add(root);

        int lastDataPos = -1; 
        while (!q.isEmpty()) {
            Node<T> n = q.remove();
            if (n == null) {
                level.add(null);
            } else {
                level.add(n.data);
                lastDataPos = level.size() - 1;
                q.add(n.left);
                q.add(n.right);
            }
        }

        //— 2. build string, trimming trailing nulls —//
        StringBuilder sb = new StringBuilder("BT(");
        for (int i = 0; i <= lastDataPos; i++) {
            Object v = level.get(i);
            if (v == null) {
                sb.append(" ");
            } else if (v instanceof String) {
                sb.append("\"").append(v).append("\"");
            } else {
                sb.append(v);
            }
            sb.append(',');
        }
        sb.setLength(sb.length() - 1); // drop final comma
        sb.append(')');
        return sb.toString();
    }

} 