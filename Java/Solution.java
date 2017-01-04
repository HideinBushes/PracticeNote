
import java.util.*;
public class Solution {
    public int[] twoSum(int[] nums, int target){
        int res[] = new int[2];
        HashMap<Integer, Integer> table = new HashMap<Integer, Integer>();
        for(int i = 0; i<nums.length; i++){
            int temp = target - nums[i];
            if(table.containsKey(temp)){
                res[0] = table.get(temp);
                res[1] = i;
                break;
            }
            else{
                table.put(nums[i], i);
            }
        }
        return res;
    }
}