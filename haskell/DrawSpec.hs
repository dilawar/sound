module DrawSpec(drawSpec) where
import Graphics.Rendering.Cairo
import Data.Array.MArray
import Array
import Data.Word
import Data.Bits

drawSpec :: [Array Int Double] -> String -> IO ()
drawSpec frames fileName =
   withImageSurface FormatRGB24 w h (drawFramesToPNG w h fileName frames)
   where w = length frames
         h = arrLength (head frames)

drawFramesToPNG :: Int -> Int -> String -> [Array Int Double] -> Surface -> IO ()
drawFramesToPNG w h filename frames srf = do
   drawFramesToSurface srf frames
   surfaceWriteToPNG srf filename

drawFramesToSurface :: Surface -> [Array Int Double] -> IO ()
drawFramesToSurface srf frames =
   mapM_ (\(column, frame) -> drawFrameToSurface srf frame column max) enumeratedFrames
      where max = getFramesMaximum frames
            enumeratedFrames = zip [0..(length frames - 1)] frames

getFramesMaximum :: [Array Int Double] -> Double
getFramesMaximum frames = foldr (\x y -> max (getFrameMaximum x) y) 0 frames

getFrameMaximum :: Array Int Double -> Double
getFrameMaximum frame = maximum [frame ! i | i <- [0..(arrLength frame - 1)]]

arrLength :: Array Int Double -> Int
arrLength arr = l + 1
   where (_,l) = bounds arr

drawFrameToSurface :: Surface -> Array Int Double -> Int -> Double -> IO ()
drawFrameToSurface srf frame column max =
   mapM_ (\(row, val) -> drawSampleToSurface srf val column row max) enumeratedVals
      where enumeratedVals = [(i, frame ! i) | i <- [0..(arrLength frame - 1)]]

drawSampleToSurface :: Surface -> Double -> Int -> Int -> Double -> IO ()
drawSampleToSurface srf val column row max = do
   srfData <- imageSurfaceGetPixels srf
   -- stride is given in bytes, we need to divide by 4 to get the width
   stride <- imageSurfaceGetStride srf
   writeArray srfData (row*(stride `div` 4)+column) (makeGrey val max)

makeGrey :: Double -> Double -> Word32
makeGrey input max =
   let scaled = floor (input / max * 0xff) in
      (shiftL 0xff 24) .|. (shiftL scaled 16) .|. (shiftL scaled 8) .|. scaled
