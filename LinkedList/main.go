package main

import (
	"fmt"
	"os"
	"strings"
)

type StringNode struct {
	value string
	next  *StringNode
}

type StringList struct {
	head *StringNode
}

func (list *StringList) Size() int {
	var sz int
	for iter := list.head; iter != nil; iter = iter.next {
		sz++
	}
	return sz
}

func (list *StringList) Empty() bool {
	return list.head == nil
}

func (list *StringList) ValueAt(index int) string {
	_, node := list.getNodeAt(index)
	return node.value
}

func (list *StringList) PushFront(value string) {
	newNode := &StringNode{value, list.head}
	list.head = newNode
}

func (list *StringList) PopFront() string {
	if list.head == nil {
		panic("cannot pop from empty list")
	}

	value := list.head.value
	list.head = list.head.next
	return value
}

func (list *StringList) PushBack(value string) {
	newNode := &StringNode{value, nil}

	if list.head == nil {
		list.head = newNode
		return
	}

	_, _, tail := list.getTailNode()
	if tail != nil {
		tail.next = newNode
	}
}

func (list *StringList) PopBack() string {
	if list.head == nil {
		panic("cannot pop from empty list")
	}

	_, prev, tail := list.getTailNode()
	if prev != nil {
		prev.next = nil
	} else {
		list.head = nil
	}
	return tail.value
}

func (list *StringList) Front() string {
	_, node := list.getNodeAt(0)
	return node.value
}

func (list *StringList) Back() string {
	_, _, tail := list.getTailNode()
	return tail.value
}

func (list *StringList) Insert(index int, value string) {
	node := &StringNode{value, nil}
	prev, iter := list.getNodeAt(index)
	if prev != nil {
		prev.next = node
	} else {
		list.head = node
	}
	node.next = iter
}

func (list *StringList) Erase(index int) {
	prev, iter := list.getNodeAt(index)
	if prev != nil {
		prev.next = iter.next
	} else {
		list.head = iter.next
	}
	iter.next = nil
}

func (list *StringList) ValueNFromEnd(n int) string {
	index, _, _ := list.getTailNode()
	_, node := list.getNodeAt(index - n)
	return node.value
}

func (list *StringList) Reverse() {
	_, prev, tail := list.getTailNode()
	if prev == nil {
		return
	}

	iter := list.head
	for iter != tail {
		n := iter.next
		iter.next = tail.next
		tail.next = iter
		iter = n
	}
	list.head = iter
}

func (list *StringList) RemoveValue(value string) bool {
	if list.head == nil {
		panic("cannot remove value from empty list")
	}

	var (
		prev *StringNode
		iter *StringNode = list.head
	)

	for iter.next != nil {
		if iter.value == value {
			if prev != nil {
				prev.next = iter.next
			} else {
				list.head = iter.next
			}
			iter.next = nil
			return true
		}

		prev = iter
		iter = iter.next
	}

	return false
}

func (list *StringList) getTailNode() (i int, p *StringNode, t *StringNode) {
	if list.head == nil {
		panic("cannot get tail of empty list")
	}

	var (
		index int
		prev  *StringNode
		tail  *StringNode = list.head
	)

	for tail.next != nil {
		prev = tail
		tail = tail.next
		index++
	}

	return index, prev, tail
}

func (list *StringList) getNodeAt(index int) (p *StringNode, i *StringNode) {
	if list.head == nil {
		panic("cannot get node of empty list")
	}

	if index < 0 {
		panic("index cannot be negative")
	}

	var (
		prev *StringNode
		iter *StringNode = list.head
	)

	for index > 0 && iter.next != nil {
		prev = iter
		iter = iter.next
		index--
	}

	if index != 0 {
		panic("out of bounds")
	}

	return prev, iter
}

func (list StringList) String() string {
	var contents []string

	for iterNode := list.head; iterNode != nil; iterNode = iterNode.next {
		contents = append(contents, iterNode.value)
	}

	return "[" + strings.Join(contents, "; ") + "]"
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("usage: ./main <words>")
		os.Exit(1)
	}

	var listOfArgs StringList
	for _, v := range os.Args[1:] {
		listOfArgs.PushBack(v)
	}
	fmt.Println(listOfArgs)

	listOfArgs.RemoveValue("uber")
	fmt.Println(listOfArgs)
}
