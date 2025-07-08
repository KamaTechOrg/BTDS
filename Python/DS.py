from __future__ import annotations
from abc import ABC, abstractmethod
from collections import deque
import re
from typing import Optional


# -------------------------
# Data Structures
# -------------------------
class ListNode:
    def __init__(self, val):
        self.val = val
        self.next: Optional['ListNode'] = None

    def __str__(self):
        vals, node = [], self
        while node:
            vals.append(str(node.val))
            node = node.next
        return " ".join(vals)

    __repr__ = __str__


class LinkedList:
    def __init__(self):
        self.head: Optional[ListNode] = None
        self.tail: Optional[ListNode] = None

    def append(self, val):
        node = ListNode(val)
        if self.head is None:
            self.head = self.tail = node
        else:
            assert self.tail is not None
            self.tail.next = node
            self.tail = node

    def __eq__(self, other):
        if not isinstance(other, LinkedList):
            return False
        node1 = self.head
        node2 = other.head
        while node1 and node2:
            if node1.val != node2.val:
                return False
            node1 = node1.next
            node2 = node2.next
        return node1 is None and node2 is None

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
        self.prev: Optional['DoublyListNode'] = None
        self.next: Optional['DoublyListNode'] = None

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
        self.head: Optional[DoublyListNode] = None
        self.tail: Optional[DoublyListNode] = None

    def append(self, val):
        node = DoublyListNode(val)
        if self.head is None:
            self.head = self.tail = node
        else:
            assert self.tail is not None
            self.tail.next = node
            node.prev = self.tail
            self.tail = node

    def __eq__(self, other):
        if not isinstance(other, DoublyLinkedList):
            return False
        node1 = self.head
        node2 = other.head
        while node1 and node2:
            if node1.val != node2.val:
                return False
            node1 = node1.next
            node2 = node2.next
        return node1 is None and node2 is None

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
        self.left: Optional['BTreeNode'] = None
        self.right: Optional['BTreeNode'] = None

    def __eq__(self, other):
        if not isinstance(other, BTreeNode):
            return False
        return (self.val == other.val and
                self.left == other.left and
                self.right == other.right)

    # ───────────────────────────── desired output ────────────────────────────
    def __str__(self) -> str:
        return self._bt_repr()

    __repr__ = __str__

    # ------------------------------------------------------------------------
    def _bt_repr(self) -> str:
        """Breadth-first (level-order) listing with blanks for missing nodes."""
        q: deque[Optional[BTreeNode]] = deque([self])  # type: ignore
        vals = []
        while q:
            n = q.popleft()
            if n is None or n.val is None:
                vals.append(" ")  # placeholder for “None”
            else:
                vals.append(str(n.val))
                # enqueue children only if at least one exists beyond this node
                if n.left or n.right:
                    if n.left is not None:
                        q.append(n.left)  # type: ignore
                    else:
                        q.append(None)  # type: ignore
                    if n.right is not None:
                        q.append(n.right)  # type: ignore
                    else:
                        q.append(None)  # type: ignore

        while vals and vals[-1] == " ":
            vals.pop()  # trim trailing blanks
        return "BT( " + ",".join(vals) + " )"
