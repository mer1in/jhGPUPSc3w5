import sys
from PIL import Image
from pathlib import Path


inputFile = Path(sys.argv[0])
print("Converting inputFile "+inputFile)
Image.open(inputFile).save(inputFile.stem+'.png')

