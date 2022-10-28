import sys
from PIL import Image
from pathlib import Path


inputFile = Path(sys.argv[1])
print("Converting inputFile "+str(inputFile))
Image.open(inputFile).save(inputFile.stem+'.png')

