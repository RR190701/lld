// Upper Bound
//First index where arr[i] > target

function upperBound(arr, target) {
  let lo = 0, hi = arr.length;

  while (lo < hi) {
    let mid = (lo + hi) >> 1;

    if (arr[mid] <= target) {
      lo = mid + 1;  // still valid, go right
    } else {
      hi = mid;      // too large, try left
    }
  }

  return lo;  // first index > target& target last index willl be  = lo-1;

  //if we want to check if the target exist in the array
  //if( lo >1 && nums[lo-1] == target)
}