package il.co.ilrd.rps;

import il.co.ilrd.Pair.Pair;

public interface ParserILRD<K,D> {
    public Pair<K,D> parse(String request);

}
