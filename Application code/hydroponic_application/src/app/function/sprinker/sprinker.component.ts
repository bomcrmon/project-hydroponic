import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';
import { environment } from 'src/environments/environment';
import { AngularFireDatabase } from '@angular/fire/compat/database';
import Swal from 'sweetalert2';

@Component({
  selector: 'app-sprinker',
  templateUrl: './sprinker.component.html',
  styleUrls: ['./sprinker.component.css'],
})
export class SprinkerComponent implements OnInit {
  sf: any = 0;
  sw: any = 0;
  setTimeFT: any;
  

  constructor(private auth: AuthService, private db: AngularFireDatabase) {}

  async ngOnInit(): Promise<void> {
    const now = new Date();

    // ดึงชั่วโมงและนาทีจาก Date object
    const hours = now.getHours();
    const minutes = now.getMinutes();
    
    // แสดงเวลาในรูปแบบที่ต้องการ (เช่น 10:30)
    const currentTime = `${hours}:${minutes}`;
    console.log(currentTime,'currentTime');
    
  }
  reset() {
    this.sf = 0;
    this.sw = 0;
  }

  startTimer() {
    // สร้าง Date object
    const now = new Date();

    // ดึงชั่วโมงและนาทีจาก Date object
    const hours = now.getHours();
    const minutes = now.getMinutes();

    // แสดงเวลาในรูปแบบที่ต้องการ (เช่น 10:30)
    const currentTime = `${hours}:${minutes}`;

    // ตรวจสอบเวลาทุกๆ 1 นาที
    setInterval(() => {
      if (currentTime === this.setTimeFT) {
        // เมื่อถึงเวลาแล้วให้อัปเดตสถานะในฐานข้อมูล
        this.db.object('relaystate/sprinkler_fertilizers').set(true);
      }
    }, 60000); // ตรวจสอบทุกๆ 1 นาที
  }

  getdata() {
    let sprinkler_fertilizers = this.db
      .object('relaystate/sprinkler_fertilizers')
      .valueChanges();
    sprinkler_fertilizers.subscribe((state: any) => {
      this.updateSwitchState('sprinkler_fertilizers', state);
    });

    let sprinkler_water = this.db
      .object('relaystate/sprinkler_water')
      .valueChanges();
    sprinkler_water.subscribe((state: any) => {
      this.updateSwitchState('sprinkler_water', state);
    });
  }

  updateSwitchState(switchId: string, state: boolean) {
    const switchElement = document.getElementById(switchId) as HTMLInputElement;
    if (switchElement) {
      switchElement.checked = state;
    }
  }

  sprinkler_fertilizers(event: any) {
    this.db.object('relaystate/sprinklerfertilizers').set(event.target.checked);
  }

  sprinkler_water(event: any) {
    this.db.object('relaystate/sprinklerwater').set(event.target.checked);
  }

  async submit() {
    await Swal.fire({
      title: `<b style="color='#000000'" class="fs-3">กดยืนยันเพื่อเติมสารเข้าถังน้ำ</b>`,
      imageUrl: 'assets/icons/delAlert.png',
      reverseButtons: true,
      showCancelButton: true,
      showCloseButton: true,
      confirmButtonColor: '#00C514',
      cancelButtonColor: '#F24E1E',
      confirmButtonText: 'ยืนยัน',
      cancelButtonText: 'ยกเลิก',
      customClass: {
        // actions: 'my-actions',
        cancelButton: 'alert-btn-cancel',
        confirmButton: 'alert-btn-confirm',
      },
    }).then(async (result) => {
      this.auth.Swal('กำลังเติมสารเข้าถังน้ำ', 'success');
      this.db
        .object('quantitysprinklerfertilizers')
        .set(this.sf)
        .then(() => console.log('finish update value'))
        .catch((error) =>
          console.error('Error updating value in Firebase:', error)
        );

      this.db
        .object('quantitysprinklerwater')
        .set(this.sw)
        .then(() => console.log('finish update value'))
        .catch((error) =>
          console.error('Error updating value in Firebase:', error)
        );
    });
  }

  SF(value: any) {
    if (value === 250) {
      this.sf = 13;
    } else if (value === 500) {
      this.sf = 26;
    }
    // else if (value === 750) {
    //   this.sf = 30;
    // }
    else {
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
      this.sw = 13;
    } else if (value === 500) {
      this.sw = 26;
    } else {
      this.sw = 0;
    }
    console.log(this.sw);
  }
}
