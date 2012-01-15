package org.apache.musicplf.service;

import java.sql.*;
import org.apache.musicplf.domain.Account;
import org.apache.musicplf.persistence.sqlmapdao.*;
import org.apache.musicplf.domain.*;

public class ArtistService
{
	private static final ArtistService instance = new ArtistService();
	private static ArtistDAOImpl artistDAOImpl = new ArtistDAOImpl();
	
	public ArtistService()
	{
		
	}
	
	public static ArtistService getInstance()
    {
	    return instance;
	}
	
	public void insertArtist(ArtistWithBLOBs accountWithBlobs) 
	throws SQLException
    {
		artistDAOImpl.insertArtist(accountWithBlobs);
	}
	
}
