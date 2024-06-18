pfimport "slices"

func maxProfitAssignment(difficulty []int, profit []int, worker []int) int {
	idx := make([]int, len(profit))
	prx := make([]int, len(profit))
	for i := range len(profit) {
		idx[i] = i
	}
	slices.SortFunc(idx, func(a, b int) int {
		return difficulty[a] - difficulty[b]
	})
	prx[0] = profit[idx[0]]
	for i := 1; i < len(profit); i++ {
		var j = i
		var pf = profit[idx[i]]
		for ; j < len(profit); j++ {
			if idx[j] == idx[i] {
				pf = max(pf, profit[idx[j]])
			} else {
				break
			}
		}
		for x := i; x < j; x++ {
			prx[x] = pf
		}
	}
	var ans = 0
	for _, w := range worker {
		i, ok := slices.BinarySearchFunc(idx, w, func(a, x int) int {
			return difficulty[a] - x
		})
		if ok {
			ans += prx[i]
		} else if i > 0 {
			ans += prx[i-1]
		}
	}
	return ans
}

func main() {
	x := maxProfitAssignment([]int{23, 30, 35, 35, 43, 46, 47, 81, 83, 98}, []int{8, 11, 11, 20, 33, 37, 60, 72, 87, 95}, []int{95, 46, 47, 97, 11, 35, 99, 56, 41, 92})
	fmt.Println(x)
}
