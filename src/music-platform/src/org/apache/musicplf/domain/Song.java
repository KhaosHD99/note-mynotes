package org.apache.musicplf.domain;

import java.util.Date;

public class Song 
{
    private Integer id;
    private String sngName;
    private String albumName;
    private String categoryName;
    private String artistName;
    private Integer price;
    private Date shelvesdate;
    private Integer clicks;
    private String remark;

    public Integer getId()
    {
        return id;
    }

    public void setId(Integer id) 
    {
        this.id = id;
    }

    public String getSngName() 
    {
        return sngName;
    }

    public void setSngName(String sngName) 
    {
        this.sngName = sngName;
    }

    public String getArtistName()
    {
        return artistName;
    }
    
    public void setArtistName(String artistName) 
    {
        this.artistName = artistName;
    }

    public String getAlbumName()
    {
        return albumName;
    }

    public void setAlbumName(String albumName) 
    {
        this.albumName = albumName;
    }

    public String getCategoryName() 
    {
        return categoryName;
    }

    public void setCategoryName(String categoryName) 
    {
        this.categoryName = categoryName;
    }

    public Date getShelvesdate()
    {
        return shelvesdate;
    }

    public void setShelvesdate(Date shelvesdate) 
    {
        this.shelvesdate = shelvesdate;
    }

    public Integer getClicks() 
    {
        return clicks;
    }

    public void setClicks(Integer clicks)
    {
        this.clicks = clicks;
    }
    
    public Integer getPrice() 
    {
        return price;
    }

    public void setPrice(Integer price)
    {
        this.price = price;
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