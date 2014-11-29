import qualified Sound.File.Sndfile as Snd
import Control.Applicative
import Foreign.Marshal.Array
import Data.Word (Word16)
import System.IO (hGetContents, Handle, openFile, IOMode(..))

format :: Snd.Format
format = Snd.Format Snd.HeaderFormatWav Snd.SampleFormatPcm16 Snd.EndianFile

openWavHandle :: [Word16] -> IO Snd.Handle
openWavHandle frames =
    let info = Snd.Info (length frames) 441000 1 format 1 False
    in Snd.openFile "temp.wav" Snd.WriteMode info

writeWav :: [Word16] -> IO Snd.Count
writeWav frames = openWavHandle frames >>= \h ->
              newArray frames >>= \ptr ->
              Snd.hPutBuf h ptr (length frames) >>= \c ->
              return c

makeWavFile :: IO ()
makeWavFile = writeWav [0..4096] >>= \c ->
          putStrLn $ "Frames written: " ++ show c


main :: IO ()
main = makeWavFile
