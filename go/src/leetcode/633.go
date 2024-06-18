package main

import "math"

func judgeSquareSum(c int) bool {
	rhs := int(math.Sqrt(float64(c)))
	var lhs = 0
	for lhs <= rhs {
		cx := rhs*rhs + lhs*lhs
		if cx == c {
			return true
		} else if cx < c {
			lhs++
		} else {
			rhs--
		}
	}
	return false
}

func main() {
	println(judgeSquareSum(4))
}
