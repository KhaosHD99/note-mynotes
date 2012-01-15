package org.apache.musicplf.presentation;

import java.io.DataInputStream;
import java.io.FileInputStream;
import org.apache.musicplf.service.*;
import org.apache.musicplf.persistence.sqlmapdao.ArtistDAOImpl;
import org.apache.musicplf.struts.BaseBean;
import org.apache.musicplf.domain.*;
import org.apache.struts.upload.FormFile;

public class ArtistBean extends BaseBean  
{
	private static final ArtistService artistService = ArtistService.getInstance();
    private ArtistWithBLOBs artistWithBlobs;
    private String artName;
   // private byte[] image;
    private boolean authenticated = false;
    private FormFile image;
    
    public ArtistBean() 
    {
  	   try
  	   {
  		 artistWithBlobs = new ArtistWithBLOBs();
  	   }
  	   catch(Exception ex)
  	   {
  		  ex.printStackTrace();
  	   }
    }
    
    public String getArtName()
    {
      return artistWithBlobs.getArtName();
    }

    public void setArtName(String artName) 
    {
      this.artistWithBlobs.setArtName(artName);
    }
    
    public FormFile getImage()
    {
    	return image;
    	
    }

    public void setImage(FormFile image) 
    {
    	try
    	{
    		this.image=image;
    	}
    	catch(Exception ex)
    	{
    		ex.printStackTrace();
    	}
    	
    }
    
    public ArtistWithBLOBs getArtistWithBLOBs()
    {
      return artistWithBlobs;
    }

    public void setArtistWithBLOBs(ArtistWithBLOBs artistWithBlobs) 
    {
      this.artistWithBlobs = artistWithBlobs;
    }
    
    public String uploadArtist()
    {
      try 
      {
    	  artistWithBlobs.setImage(image.getFileData());
          artistService.insertArtist(artistWithBlobs);
  		  return "success";
      } 
      catch (Exception e)
      {
      	  e.printStackTrace();
      	  return "failure";
      }
    }
}
