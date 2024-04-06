import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';
import { environment } from 'src/environments/environment';
import { AngularFireDatabase } from '@angular/fire/compat/database';

@Component({
  selector: 'app-quantity',
  templateUrl: './quantity.component.html',
  styleUrls: ['./quantity.component.css'],
})
export class QuantityComponent implements OnInit {
  Fer: any;
  Mb: any;
  phUp: any;
  phD: any;
  sf: any;
  sw: any;
  
  item: any = [{ id: 1, name: '250' },{ id: 2, name: '500' },{ id: 3, name: '750' },];
  constructor(private auth: AuthService, private db: AngularFireDatabase) {}
  ngOnInit(): void {}

  FT(value: any) {
    if (value === 250) {
      this.Fer = 10;
    } else if (value === 500) {
      this.Fer = 20;
    } else if (value === 750) {
      this.Fer = 30;
    } else {
      this.Fer = 0;
    }
    console.log(this.Fer);

    this.db
      .object('quantityFT')
      .set(this.Fer)
      .then(() => console.log('finish update value'))
      .catch((error) =>
        console.error('Error updating value in Firebase:', error)
      );
  }

  MB(value: any) {    
    if (value === 250) {
      this.Mb = 10;
    } else if (value === 500) {
      this.Mb = 20;
    } else if (value === 750) {
      this.Mb = 30;
    } else {
      this.Mb = 0;
    }
    console.log(this.Mb);

    this.db
      .object('quantityMB')
      .set(this.Mb)
      .then(() => console.log('finish update value'))
      .catch((error) =>
        console.error('Error updating value in Firebase:', error)
      );
  }

  PhUp(value: any) {    
    if (value === 250) {
      this.phUp = 10;
    } else if (value === 500) {
      this.phUp = 20;
    } else if (value === 750) {
      this.phUp = 30;
    } else {
      this.phUp = 0;
    }
    console.log(this.phUp);

    this.db
      .object('quantityphdown')
      .set(this.phUp)
      .then(() => console.log('finish update value'))
      .catch((error) =>
        console.error('Error updating value in Firebase:', error)
      );
  }

  PhD(value: any) {    
    if (value === 250) {
      this.phD = 10;
    } else if (value === 500) {
      this.phD = 20;
    } else if (value === 750) {
      this.phD = 30;
    } else {
      this.phD = 0;
    }
    console.log(this.phD);

    this.db
      .object('quantityphup')
      .set(this.phD)
      .then(() => console.log('finish update value'))
      .catch((error) =>
        console.error('Error updating value in Firebase:', error)
      );
  }

  SF(value: any) {    
    if (value === 250) {
      this.sf = 10;
    } else if (value === 500) {
      this.sf = 20;
    } else if (value === 750) {
      this.sf = 30;
    } else {
      this.sf = 0;
    }
    console.log(this.sf);

    this.db
      .object('quantitysprinklerfertilizers')
      .set(this.sf)
      .then(() => console.log('finish update value'))
      .catch((error) =>
        console.error('Error updating value in Firebase:', error)
      );
  }

  SW(value: any) {    
    if (value === 250) {
      this.sw = 10;
    } else if (value === 500) {
      this.sw = 20;
    } else if (value === 750) {
      this.sw = 30;
    } else {
      this.sw = 0;
    }
    console.log(this.sw);

    this.db
      .object('quantitysprinklerwater')
      .set(this.sw)
      .then(() => console.log('finish update value'))
      .catch((error) =>
        console.error('Error updating value in Firebase:', error)
      );
  }
}
