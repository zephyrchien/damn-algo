package main

func groups(bloomDay []int, k, today int) int {
	var cnt = 0
	var total = 0
	for _, day := range bloomDay {
		if day > today {
			cnt = 0
			continue
		}
		cnt++
		if cnt == k {
			total++
			cnt = 0
		}
	}
	return total
}

func minDays(bloomDay []int, m int, k int) int {
	if len(bloomDay) < m*k {
		return -1
	}
	lhs, rhs := 0, int(1e9+1)
	for lhs < rhs {
		mid := (lhs + rhs) / 2
		if n := groups(bloomDay, k, mid); n < m {
			lhs = mid + 1
		} else {
			rhs = mid
		}
	}
	return lhs
}
