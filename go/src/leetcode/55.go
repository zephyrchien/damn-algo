package main

func canJump(nums []int) bool {
	dp := make([]bool, len(nums))
	dp[0] = true
	for i := 0; i < len(nums); i++ {
		if !dp[i] {
			continue
		}
		for j := 1; j <= nums[i] && i+j < len(nums); j++ {
			dp[i+j] = true
		}
	}
	return dp[len(nums)-1]
}

func main() {

}
