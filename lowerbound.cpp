//Lower Bound
//First index where arr[i] ≥ target

function lowerBound(arr, target) {
  let lo = 0, hi = arr.length;

  while (lo < hi) {
    let mid = (lo + hi) >> 1;

    if (arr[mid] < target) {
      lo = mid + 1;  // too small, go right
    } else {
      hi = mid;      // valid, try left
    }
  }

  return lo;  // first index >= target 
    //if we want to check if the target exist in the array
  //if( lo < nums.size() && nums[lo] == target)
}