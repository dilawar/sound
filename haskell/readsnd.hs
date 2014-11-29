import qualified Sound.File.Sndfile as Snd
import qualified Sound.File.Sndfile.Buffer.StorableVector as BV
import qualified Data.StorableVector as V
import Data.Array as A
import Data.Complex
import DSP.Basic
import Numeric.Transform.Fourier.FFT
import DrawSpec
import System.Environment (getArgs)

sndFileName = "../testSamples/5650__pushtobreak__valihaloop5-5.aif"

readWavFile :: String -> IO (V.Vector Double)
readWavFile fileName = do
   handle <- Snd.openFile fileName Snd.ReadMode Snd.defaultInfo
   (info, Just buf) <- Snd.hGetContents handle :: IO (Snd.Info, Maybe (BV.Buffer Double))
   return (BV.fromBuffer buf)

arrayFromVector :: V.Vector Double -> A.Array Int Double
arrayFromVector vect =
   let l = V.length vect - 1 in
      A.array (0, l) (zip [0..l] (V.unpack vect))

getFrames :: A.Array Int Double -> Int -> Int -> [A.Array Int Double]
getFrames inArr frameSize hop =
   [getFrame inArr start frameSize | start <- [0, hop .. l-1]]
   where
      (_,l) = A.bounds inArr

-- getFrame uses ixmap to create a new array that's a slice of
-- the old one. The bounds of the new array are 0 and the length,
-- the transformation function to get an index into the original
-- array from the new array is just an offset operation.
getFrame :: A.Array Int Double -> Int -> Int -> A.Array Int Double
getFrame inVect start length = pad slice length
   where
      slice = A.ixmap (0, l - 1) (+ start) inVect
      l = min length (end - start)
      (_,end) = A.bounds inVect

getMagnitude :: [A.Array Int (Complex Double)] -> [A.Array Int Double]
getMagnitude frames = map getFrameMagnitude frames

getFrameMagnitude :: A.Array Int (Complex Double) -> A.Array Int Double
getFrameMagnitude frame = A.array (0,(l-1)`div`2) [(i,log (magnitude (frame!(i+(l-1)`div`2)) + 1)) | i <- [0..((l-1)`div`2)]]
   where (_,l) = A.bounds frame

main :: IO ()
main = do
   filename <- getArgs
   audioVect <- readWavFile $ head filename
   drawSpec (map (getFrameMagnitude . rfft) (getFrames (arrayFromVector audioVect) 1024 512)) "spec.png"
