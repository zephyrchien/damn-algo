package main

import "fmt"

func twoSum(nums []int, target int) [2]int {
	tb := make(map[int]int, 32)
	for idx, num := range nums {
		want := target - num
		if idx2, ok := tb[want]; ok {
			return [2]int{idx, idx2}
		}
		tb[num] = idx
	}
	return [2]int{-1, -1}
}

func main() {
	fmt.Println(twoSum([]int{2, 7, 11, 15}, 9))
}
