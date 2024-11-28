import sys
import bitcoin
import hashlib
import txnUtils
import keyUtils

#tx = ""
# tx = "" + sys.argv[1]
tx="0100000001599b576edb0e0bf62082a30ff974d04080bfadb4dd9154f4e8949ea8da4c15182c0000006a4730440220061e5f5c2bc146cd5070cdef9cd2376a0b2fbbdbbda698858a38190d06caf1ff0220649db1b4fbaaba2d0669f7f7635157b273146b064248d04e76c25d41971d99a1012103f3b587144f038f7fd504eaebb2159ad97c0ca33c3cbaf7f3899849a9e2c9074bffffffff010000000000000000046a02585800000000"
m = txnUtils.parseTxn(tx)
e = txnUtils.getSignableTxn(m)
z = hashlib.sha256(hashlib.sha256(bytes.fromhex(e)).digest()).digest()
z1 = z[::-1].hex()
z = z.hex()
s = keyUtils.derSigToHexSig(m[1][:-2])
pub =  m[2]
sigR = s[:64]
sigS = s[-64:]
sigZ = z

print ("R = 0x" + sigR + "")
print ("S = 0x" + sigS + "")
print ("Z = 0x" + sigZ + "")
print ("")
