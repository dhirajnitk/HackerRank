import itertools 
BIT_SIZE = 32
def getBit(n,k):
    return (n & (1<<k)) != 0

def bitWiseOR(arr):
    result= 0
    #bitFreq = [0 for i  in range(BIT_SIZE)]
    #bitFreq = list(itertools.repeat(0, BIT_SIZE))
    bitFreq = [0] * BIT_SIZE
    for i in range(len(arr)):
         for k in list(reversed(range(BIT_SIZE))):
            bitFreq[k]+= getBit(arr[i],k);

    for i in range(BIT_SIZE):
        while(bitFreq[i]):
            result+= pow(2,i)*pow(2,len(arr)-bitFreq[i])
            bitFreq[i]-=1
    return result
if __name__ == "__main__":
    arr= [1, 2 , 3 ]
    print(bitWiseOR(arr))