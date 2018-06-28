TEMPFILE=__yazid__tmp.in

make encryptor
for ((i=$1;i<=$2;++i)); do
	echo Encrypting Data#$i...
	./encryptor <$i.in >${TEMPFILE}
	mv ${TEMPFILE} $i.in
done
