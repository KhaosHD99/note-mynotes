package org.apache.musicplf.domain;

public class ArtistWithBLOBs extends Artist 
{
   private byte[] image;

   private String remark;

   public byte[] getImage() 
   {
        return image;
   }

   public void setImage(byte[] image) 
   {
        this.image = image;
   }

   public String getRemark()
   {
        return remark;
   }

   
   public void setRemark(String remark) 
   {
        this.remark = remark;
   }
}