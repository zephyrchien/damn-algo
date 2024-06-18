package main

func solve1(nums []int) int {
	len := len(nums)
	dp := make([]int, len)
	dp[0] = 1
	for i := 1; i < len; i++ {
		var m = 1
		for j := 0; j < i; j++ {
			if nums[i] > nums[j] {
				m = max(m, dp[j]+1)
			}
		}
		dp[i] = m
	}
	var ans = 0
	for i := 0; i < len; i++ {
		ans = max(ans, dp[i])
	}
	return ans
}

func main() {
	solve1([]int{4, 10, 4, 3, 8, 9})
}
