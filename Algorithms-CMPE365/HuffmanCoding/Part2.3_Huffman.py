import glob
import errno
import heapq

# Characters ranging from 32->126 and line-feed (#10)
numOfChars = 96


# Define class to hold contents of Huffman node
class HuffmanNode:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq


# Initialize array to be used for min heap
asciiFrequencies = []
for i in range(numOfChars):
    asciiFrequencies.append(0)


# Define character frequency function
def charFrequency(files):
    for fileName in files:
        try:
            with open(fileName) as f:
                while True:
                    c = f.read(1)
                    if not c:
                        break
                    if ord(c) == 10:
                        asciiFrequencies[0] = asciiFrequencies[0] + 1
                    asciiFrequencies[ord(c) - 31] = asciiFrequencies[ord(c) - 31] + 1
        except IOError as exc:
            if exc.errno != errno.EISDIR:
                raise


# Function to read text files
def CanonicalReads(pathIn):
    fileList = glob.glob(pathIn)
    charFrequency(fileList)


# Read each canonical set
CanonicalReads('C:/Users/andre/PycharmProjects/HuffmanCoding/Canonical_3/*.txt')


# Create list of Huffman Node Objects for each ASCII character
nodeList = []
nodeList.append(HuffmanNode(chr(10), asciiFrequencies[0]))
for i in range(numOfChars):
    nodeList.append(HuffmanNode(chr(i + 31), asciiFrequencies[i]))

# Heap sort the list of node objects
objectHeap = []
for node in nodeList:
    heapq.heappush(objectHeap, node)

# Create basis for Huffman Tree Structure by assigning parents and children
while len(objectHeap) > 1:
    node1 = heapq.heappop(objectHeap)
    node2 = heapq.heappop(objectHeap)
    merged = HuffmanNode(None, node1.freq + node2.freq)
    merged.left = node1
    merged.right = node2
    heapq.heappush(objectHeap, merged)  # Push merged node back into object heap

# Initialize the Code List
codeList = []
for i in range(numOfChars):
    codeList.append(0)
# Used for decoding
reverseCodeList = []
for i in range(numOfChars):
    reverseCodeList.append(0)
# Initialize the Huffman Code
currentHuffCode = ""
# Take the final object from the heap as the parent node
root = heapq.heappop(objectHeap)


# Create code list array
def makeCode(rootNode, code):
    if rootNode is None:
        return
    if rootNode.char is not None:
        if ord(rootNode.char) == 10:
            codeList[0] = code
        else:
            codeList[ord(rootNode.char) - 31] = code
    makeCode(rootNode.left, code + "0")
    makeCode(rootNode.right, code + "1")


makeCode(root, currentHuffCode)

# Load text file with codes for each ASCII char
dummy = 0
file = open("Part2.3_asciiFrequencies.txt", "w+")
file.write("{} {}\n".format(10, codeList[0]))
for item in codeList[1:]:
    file.write("{} {}\n".format((dummy + 32), item))
    dummy = dummy + 1
file.close()

codeDictionary = []
# Load code dictionary from text file
with open('C:/Users/andre/PycharmProjects/HuffmanCoding/Part2.3_asciiFrequencies.txt') as textFile:
    for line in textFile:
        codeDictionary.append(line.split(' ')[1])

# Code array will now contain each bit sequence without /n char
for i in range(96):
    codeDictionary[i] = codeDictionary[i].rstrip()

# Determine file to encode
pathToEncode1 = 'C:/Users/andre/PycharmProjects/HuffmanCoding/Data/EarthASCII.txt'
pathToEncode2 = 'C:/Users/andre/PycharmProjects/HuffmanCoding/Data/MysteryASCII.txt'
pathToEncode3 = 'C:/Users/andre/PycharmProjects/HuffmanCoding/Data/MythsASCII.txt'
pathToEncode4 = 'C:/Users/andre/PycharmProjects/HuffmanCoding/Data/SimakASCII.txt'
pathToEncode5 = 'C:/Users/andre/PycharmProjects/HuffmanCoding/Data/WodehouseASCII.txt'
# Clear output text file that will be written to
encodeOutput = 'C:/Users/andre/PycharmProjects/HuffmanCoding/Data/TestOutput_2.3.txt'
open(encodeOutput, 'w').close()


# Encode Text
def EncodeText(encodingPath, encodingOutput):
    encodedArray = ''
    with open(encodingPath) as f:
        while True:
            c = f.read(1)
            if not c:
                print("End of file")
                break
            if ord(c) == 10:
                encodedArray = encodedArray + (codeDictionary[0])
            else:
                encodedArray = encodedArray + (codeDictionary[ord(c) - 31])
        return encodedArray


# Get encoded bits for each data file
array1 = EncodeText(pathToEncode1, encodeOutput)
array2 = EncodeText(pathToEncode2, encodeOutput)
array3 = EncodeText(pathToEncode3, encodeOutput)
array4 = EncodeText(pathToEncode4, encodeOutput)
array5 = EncodeText(pathToEncode5, encodeOutput)

# Write encoded arrays to output file
with open(encodeOutput, 'r') as infile:
    data = infile.read() + array1
with open(encodeOutput, 'w') as outfile:
    outfile.write(data)
with open(encodeOutput, 'r') as infile:
    data = infile.read() + array2
with open(encodeOutput, 'w') as outfile:
    outfile.write(data)
with open(encodeOutput, 'r') as infile:
    data = infile.read() + array3
with open(encodeOutput, 'w') as outfile:
    outfile.write(data)
with open(encodeOutput, 'r') as infile:
    data = infile.read() + array4
with open(encodeOutput, 'w') as outfile:
    outfile.write(data)
with open(encodeOutput, 'r') as infile:
    data = infile.read() + array5
with open(encodeOutput, 'w') as outfile:
    outfile.write(data)

# TestOutput.txt File1ASCII.txt
