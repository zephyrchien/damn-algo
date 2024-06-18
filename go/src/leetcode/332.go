package main

func coinChange(coins []int, amount int) int {
	dp := make([]int, amount+1)
	for i := 1; i <= amount; i++ {
		var cnt = -1
		for _, c := range coins {
			if i >= c && dp[i-c] >= 0 {
				if cnt < 0 {
					cnt = dp[i-c]
				} else {
					cnt = min(cnt, dp[i-c])
				}
			}
		}
		if cnt >= 0 {
			dp[i] = cnt + 1
		} else {
			dp[i] = -1
		}
	}
	return dp[amount]
}

func main() {

}
