package org.apache.musicplf.domain;

import java.util.Date;
import java.io.DataInputStream;
import java.io.FileInputStream;

public class SongWithBLOBs extends Song
{
  
    private byte[] songFile;
    
    public byte[] getSongFile() 
    {
        return songFile;
    }

    public void setSongFile(byte[] songFile) 
    {
        this.songFile = songFile;
    }
    
}
