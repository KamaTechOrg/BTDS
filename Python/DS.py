from abc import ABC, abstractmethod
from collections import deque


# -------------------------
# Data Structures
# -------------------------
class ListNode:
    def __init__(self, val):
        self.val = val
        self.next = None

    def __str__(self):
        vals, node = [], self
        while node:
            vals.append(str(node.val))
            node = node.next
        return " ".join(vals)

    __repr__ = __str__


class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def append(self, val):
        node = ListNode(val)
        if self.head is None:
            self.head = self.tail = node
        else:
            self.tail.next = node
            self.tail = node

    def __getattr__(self, name):
        # Forward any attribute access to self.head
        return getattr(self.head, name)

    def __str__(self) -> str:
        vals, node = [], self.head
        while node:
            vals.append(str(node.val))
            node = node.next
        return f"LL( {', '.join(vals)} )"

    __repr__ = __str__


class DoublyListNode:
    def __init__(self, val):
        self.val = val
        self.prev = None
        self.next = None

    def __str__(self):
        # Print from list-head
        head = self
        while head.prev:
            head = head.prev

        vals = []
        node = head
        while node:
            vals.append(str(node.val))
            node = node.next
        return " <-> ".join(vals)

    __repr__ = __str__


class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def append(self, val):
        node = DoublyListNode(val)
        if self.head is None:
            self.head = self.tail = node
        else:
            self.tail.next = node
            node.prev = self.tail
            self.tail = node

    def __str__(self) -> str:
        vals, node = [], self.head
        while node:
            vals.append(str(node.val))
            node = node.next
        return f"DLL( {', '.join(vals)} )"

    __repr__ = __str__


from collections import deque


class BTreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

    
    def __str__(self) -> str:
        return self._bt_repr()

    __repr__ = __str__

    def _bt_repr(self) -> str:
        """Breadth-first (level-order) listing with blanks for missing nodes."""
        q, vals = deque([self]), []
        while q:
            n = q.popleft()
            if n is None:
                vals.append(" ")  # placeholder for “None”
            else:
                vals.append(str(n.val))
                # enqueue children only if at least one exists beyond this node
                if n.left or n.right:
                    q.append(n.left)
                    q.append(n.right)

        while vals and vals[-1] == " ":
            vals.pop()  # trim trailing blanks
        return "BT( " + ",".join(vals) + " )"